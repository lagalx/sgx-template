#include <stdio.h>
#include <tchar.h>
#include <string.h>

#include <sgx_urts.h>
#include <sgx_tseal.h>
#include "enclave_u.h"

#define ENCLAVE_FILE _T("enclave.signed.dll") 

#define BUF_LEN 100

int main() {
    char buffer[BUF_LEN] = { 0 };

    //�������� � ������������� ������� 
    sgx_enclave_id_t eid;
    sgx_status_t ret = SGX_SUCCESS;
    sgx_launch_token_t token = { 0 };
    int updated = 0;

    ret = sgx_create_enclave(ENCLAVE_FILE, SGX_DEBUG_FLAG, &token, &updated, &eid, NULL); //��������
    if (ret != SGX_SUCCESS) { //�������� ������������ ��������
        printf("App: error %#x, failed to create enclave.\n", ret);
        return -1;
    }

    //����������� ������ ������ ������� �� ������������ 
    while (true) {
        printf("Input index to retrive, or -1 to exit: \t");
        int idx = -1;
        scanf_s("%d", &idx);
        if (idx < 0) {
            return 0;
        }
        get_table(eid, buffer, BUF_LEN, idx);
        printf("%s\n=======================\n\n", buffer);
    }

    //�������� �������
    if (SGX_SUCCESS != sgx_destroy_enclave(eid))
        return -1;

    return 0;
}