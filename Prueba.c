#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

// Funciones de FUSE

static int vfat_getattr(const char *path, struct stat *stbuf)
{
    // Implementa la función getattr para obtener atributos de archivos y directorios
    // según el path proporcionado
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

static int vfat_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    // Implementa la función readdir para leer el contenido de un directorio
    // y llenar el buffer utilizando la función filler
    
    return 0;
}

static int vfat_open(const char *path, struct fuse_file_info *fi)
{
    // Implementa la función open para abrir un archivo
    
    return 0;
}

static int vfat_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    // Implementa la función read para leer datos desde un archivo
    
    return 0;
}

static int vfat_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fi)
{
    // Implementa la función write para escribir datos en un archivo
    
    return 0;
}

static int vfat_create(const char *path, mode_t mode, struct fuse_file_info *fi)
{
    // Implementa la función create para crear un nuevo archivo
    
    return 0;
}

static int vfat_mkdir(const char *path, mode_t mode)
{
    // Implementa la función mkdir para crear un nuevo directorio
    
    return 0;
}

static int vfat_borrar(const char *path)
{
    // Implementa la función unlink para eliminar un archivo
    
    return 0;
}

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

int main(int argc, char *argv[])
{
    // Monta el sistema de archivos vFAT utilizando FUSE
    return fuse_main(argc, argv, &vfat_operations, NULL);
}
