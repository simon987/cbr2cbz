#include <archive.h>
#include <string.h>
#include <wordexp.h>
#include <stdlib.h>

#define ARC_BUF_SIZE 8192

char *abspath(const char *path) {
    char *abs = realpath(path, NULL);
    if (abs == NULL) {
        return NULL;
    }

    return abs;
}

void convert_cbr(char *rar_in_path) {

    if (strstr(rar_in_path, ".cbr") == NULL) {
        fprintf(stderr, "Input file does not have .cbr extension");
        return;
    }

    char zip_out_path[4096];
    strcpy(zip_out_path, rar_in_path);
    memcpy(strstr(zip_out_path, ".cbr"), ".cbz\0", 5);

    struct stat _;
    if (stat(zip_out_path, &_) == 0) {
        return;
    }

    struct archive *rar_in = archive_read_new();
    archive_read_support_filter_none(rar_in);
    archive_read_support_format_rar(rar_in);
    archive_read_support_format_rar5(rar_in);

    int ret = archive_read_open_filename(rar_in, rar_in_path, ARC_BUF_SIZE);
    if (ret != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(rar_in));
        return;
    }

    struct archive *zip_out = archive_write_new();
    archive_write_set_format_zip(zip_out);
    ret = archive_write_open_filename(zip_out, zip_out_path);
    if (ret != ARCHIVE_OK) {
        fprintf(stderr, "%s\n", archive_error_string(zip_out));
        return;
    }


    struct archive_entry *entry;
    while (archive_read_next_header(rar_in, &entry) == ARCHIVE_OK) {
        archive_write_header(zip_out, entry);

        char arc_buf[ARC_BUF_SIZE];
        int len = archive_read_data(rar_in, arc_buf, ARC_BUF_SIZE);
        while (len > 0) {
            archive_write_data(zip_out, arc_buf, len);
            len = archive_read_data(rar_in, arc_buf, ARC_BUF_SIZE);
        }
    }

    archive_write_close(zip_out);
    archive_write_free(zip_out);

    archive_read_close(rar_in);
    archive_read_free(rar_in);
}

int main(int argc, char **argv) {

    if (argc == 1) {
        fprintf(stderr, "USAGE: cbr2cbz FILE...\n");
    }

    for (int i = 1; i < argc; i++) {
        char *abs = abspath(argv[i]);

        if (abs == NULL) {
            fprintf(stderr, "File not found: '%s'\n", argv[i]);
            continue;
        }
        convert_cbr(abs);
        free(abs);
    }
}
