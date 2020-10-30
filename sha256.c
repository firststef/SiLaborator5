#include <stdio.h>

#include <openssl/evp.h>

#include <openssl/err.h>

#include <string.h>



void handleErrors(void)

{

    ERR_print_errors_fp(stderr);

    abort();

}



void digest_message_sha256(const unsigned char *message, size_t message_len, unsigned char **digest, unsigned int *digest_len)

{

    EVP_MD_CTX *mdctx;



    //aici in versiunea trecuta era  EVP_MD_CTX_new() 

    if((mdctx = EVP_MD_CTX_create()) == NULL)

        handleErrors();



    if(1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL))

        handleErrors();



    if(1 != EVP_DigestUpdate(mdctx, message, message_len))

        handleErrors();



    if((*digest = (unsigned char *)OPENSSL_malloc(EVP_MD_size(EVP_sha256()))) == NULL)

        handleErrors();



    if(1 != EVP_DigestFinal_ex(mdctx, *digest, digest_len))

        handleErrors();

    

    //aici in versiunea trecuta era  EVP_MD_CTX_free() 

    EVP_MD_CTX_destroy(mdctx);

}



void writeHashToFile(char* fileName, unsigned char *digest, int digest_len)

{

    int i;

    FILE* f = fopen(fileName,"w");

    for(i=0;i<digest_len;i++)

        fprintf(f,"%02x",digest[i]);

    fclose(f);

}



int main(int argc, char** argv)

{

    int i;

    if(argc != 3)

    {

        printf("Utilizare: %s <fisier_input> <fisier_output> ",argv[0]);

        return 1;

    }



    FILE* f1 = fopen(argv[1],"r");

    char content1[50000]="";

    char* line = (char*)malloc(256);



    while( fgets(line,256,f1) != NULL)

    {

        strcat(content1,line);

    }

    fclose(f1);



    unsigned char *digest1;

    int digest1_len;



    //calculam md5 pentru fisierul de intrare:



    printf("Calculam md5 pt fisierul %s cu output in %s\n", argv[1], argv[2]);



    digest_message_sha256(content1,strlen(content1), &digest1, &digest1_len);

    writeHashToFile(argv[2],digest1, digest1_len);

//    BIO_dump_fp (stdout, (const char *)digest1, digest1_len);



    return 0;



}
