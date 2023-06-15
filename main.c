#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

// Ruta al directorio raíz de la tabla vFAT
const char* vfat_root = "/home";

// ***** Funciones de FUSE  *******

// Implementa la función getattr para obtener atributos de archivos y directorios según el path proporcionado
static int vfat_getattr(const char *path, struct stat *stbuf){
    int res = 0;

    // Comprueba si es la raíz del sistema de archivos
    if (strcmp(path, "/") == 0) {
        // Asigna los atributos de la raíz
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    }
    else {
        // Asigna los atributos de un archivo o directorio regular
        stbuf->st_mode = S_IFREG | 0644;
        stbuf->st_nlink = 1;
        stbuf->st_size = <tamaño del archivo>; // Asigna el tamaño del archivo
    }
    
    return res;
}

// Implementa la función readdir para leer el contenido de un directorio y llenar el buffer utilizando la función filler
static int vfat_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    
    return 0;
}

// Implementa la función open para abrir un archivo
static int vfat_open(const char *path, struct fuse_file_info *fi) {
    // Ruta completa del archivo
    char full_path[40];
    sprintf(full_path, "%s%s", vfat_root, path);

    // Abrir el archivo en modo lectura
    FILE* file = fopen(full_path, "rb");
    if (file == NULL) {
        return -ENOENT;
    }

    // Almacenar el puntero de archivo en el campo 'fh' de 'fuse_file_info'
    fi->fh = (uintptr_t)file;

    return 0;
}

// Implementa la función que lee el contenido de un archivo
static int vfat_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
   // Obtiene el descriptor de archivo
    int fd = fi->fh;

    // Mueve el puntero de lectura al desplazamiento especificado en el offset
    if (lseek(fd, offset, SEEK_SET) == -1){
        return -errno;
    }

    // Lee los datos del archivo
    ssize_t bytesRead = read(fd, buf, size);
    if (bytesRead== -1){
        return -errno;
    }

    //Retorna el número de bytes leídos
    return bytesRead;
}

 // Implementa la función write para escribir datos en un archivo
static int vfat_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi){
   
    return 0;
}

// Implementa la función create para crear un nuevo archivo
static int vfat_create(const char *path, mode_t mode, struct fuse_file_info *fi){
    
    return 0;
}

// Implementa la función mkdir para crear un nuevo directorio
static int vfat_mkdir(const char *path, mode_t mode){
    
    
    return 0;
}

// Implementa la función para eliminar un archivo
static int vfat_delete(const char *path){

    // Ruta completa del archivo
    char full_path[40];
    sprintf(full_path, "%s%s", vfat_root, path);

    // Elimina el archivo utilizando la función remove() de la biblioteca estándar
    int result = remove(full_path);
    if (result == -1) {
        return -errno;
    }

    return 0;
}

// Struct que enlaza la tabla vFAt con las funciones del FUSE
static struct fuse_operations vfat_operations = {
    .getattr    = vfat_getattr,
    .readdir    = vfat_readdir,
    .open       = vfat_open,
    .read       = vfat_read,
    .write      = vfat_write,
    .create     = vfat_create,
    .mkdir      = vfat_mkdir,
    .unlink     = vfat_borrar,
};

// Función Main 
int main(int argc, char *argv[]) {
    // Monta el sistema de archivos vFAT utilizando FUSE
    return fuse_main(argc, argv, &vfat_operations, NULL);
}
