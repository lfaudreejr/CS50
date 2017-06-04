# ===== Imports ===== #
import cs50
import sys
import crypt
# ===== Main Program =====#

def main():
    cipher_text = get_ciphertext()
    
    cracked = break_word(cipher_text)
    
    if cracked:
        print("The cracked password is: ")
        print(cracked)
    else:
        print("Could not crack")
    
    # crypt.crypt(salt, word)

# ===== User Input ===== #
def get_ciphertext():
    if len(sys.argv) >= 2:
        ciphertext = ''.join(sys.argv[1:])
    else:
        return "Please enter valid ciphertext!"
    return ciphertext
    
    
    
# ===== Generate words ===== #

def break_word(cipher):
    letters = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz'
    ciphered_text = cipher
    
    for a in letters:
        plaintext1 = a
        word = plaintext1
        hashed_text = crypt.crypt(plaintext1, "50")
        
        if hashed_text == ciphered_text:
            return word
        else:
            for b in letters:
                plaintext2 = b
                word = plaintext1 + plaintext2
                hashed_text = crypt.crypt(word, "50")
                
                if hashed_text == ciphered_text:
                    return word
                else:
                    for c in letters:
                        plaintext3 = c
                        word = plaintext1 + plaintext2 + plaintext3
                        hashed_text = crypt.crypt(word, "50")
                        
                        if hashed_text == ciphered_text:
                            return word
                        else:
                            for d in letters:
                                plaintext4 = d
                                word = plaintext1 + plaintext2 + plaintext3 + plaintext4
                                hashed_text = crypt.crypt(word, "50")
                                
                                if hashed_text == ciphered_text:
                                    return word

    
# ===== Start Program ===== #
main()