#include "pe_hdrs_helper.h"

IMAGE_NT_HEADERS* get_nt_hrds(BYTE *pe_buffer)
{
    if (pe_buffer == NULL) return NULL;

    IMAGE_DOS_HEADER *idh = (IMAGE_DOS_HEADER*)pe_buffer;
    if (idh->e_magic != IMAGE_DOS_SIGNATURE) {
        return NULL;
    }
    IMAGE_NT_HEADERS *inh = (IMAGE_NT_HEADERS *)((BYTE*)pe_buffer + idh->e_lfanew);
    if (inh->Signature == IMAGE_NT_SIGNATURE) {
        return inh;
    }
    return NULL;
}

IMAGE_DATA_DIRECTORY* get_pe_directory(PVOID pe_buffer, DWORD dir_id)
{
    if (dir_id > 16) return NULL;

    //fetch relocation table from current image:
    PIMAGE_NT_HEADERS nt_headers = get_nt_hrds((BYTE*) pe_buffer);
    if (nt_headers == NULL) return NULL;

    IMAGE_DATA_DIRECTORY* peDir = &(nt_headers->OptionalHeader.DataDirectory[dir_id]);
    if (peDir->VirtualAddress == NULL) {
        return NULL;
    }
    return peDir;
}
