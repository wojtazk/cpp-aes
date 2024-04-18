# Advanced Encryption Algorithm with 128-bit key

my implementation of AES in C++


## Info

word size: `32 bit`  
key length: `128 bit` -> `4 words`  
block size: `128 bit` -> `4 words`  
number of rounds: `10`

## Usage

>[!NOTE]
>The program will ask you to enter the key  
>The key in my implementation is kind of like a password provided by user
>
>If the string provided by user is too long -> only first 16 bytes are treated as a key  
>If it is too short -> the remaining bytes are filled with '0'

### Encryption

```bash
./cpp-aes -e input_file output_file
```

### Decryption

```bash
./cpp-aes -d input_file output_file
```

### Usage Example

![image](https://github.com/wojtazk/cpp-aes/assets/48928433/8ca16702-6a25-4f00-9bb4-e1e1759b6b83)

## Resources

- https://blog.nindalf.com/posts/implementing-aes/
- https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.197.pdf
- https://engineering.purdue.edu/kak/compsec/NewLectures/Lecture8.pdf
- https://en.wikipedia.org/wiki/Rijndael_S-box
- https://en.wikipedia.org/wiki/Rijndael_mix_columns
- https://en.wikipedia.org/wiki/Rijndael_key_schedule#Rcon
