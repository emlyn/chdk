#ifndef _AES128__H_
#define _AES128__H_

void aes128_expandkey( void *expanded_key, const void *aes_key );
void aes128_encrypt_block (void *out_buffer, const void *inp_buffer, const unsigned char *expkey );
void aes128_decrypt_block (void *out_buffer, const void *inp_buffer, const unsigned char *expkey );
void aes128_cbc_encrypt( void *buffer, const unsigned char *expkey, const void *iv, int len );
void aes128_cbc_decrypt( void *buffer, const unsigned char *expkey, const void *iv, int len );

#endif // _AES128__H_
