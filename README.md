# Bornomala-Symmetric-Key (BSK) Stream Cipher
[![forthebadge](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)](https://forthebadge.com)[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

<p align = "center">
<img src = "images/crypto.jpg" width = "200"> <br> 
<a href="#key-generation">Key Generation</a> • <a href="#encryption">Encryption</a> • <a href="#decryption">Decryption</a> • <a href="#advantages">Advantages</a> •
</p>

---
Key Generation
---

**Requirement:**
- A strong key is required, a minimum of 8 characters
- Key must have to contain uppercase, lowercase, and digits. 
- No Space is allowed in a key

> Generated-Key is similar with hashing <br>
> Unless fixed length hashing, the generated key is of any size depanding on inputs message [variable-length hashing]

**Key Generation Process** <br>
Roughly divided into three sections:
* Key Enhancement
* Key Substitution
* Random-indexing shuffle

**Example:** <br>

 Let's assume:<p align = "center">
  Initial Key (K) = **HstU@5200** <br>
  Message (M) = **Hajee DanesH 26/10/19**
</p>

 Then:<p align = "center">
  Enhanced Key = **HstU@5200HstU@5200Hst** <br>
  Substitute Key = **6u,b.X(V'(g}T JyHxyYo** <br>
  R-I Shuffle = **,(V6T.xu 'boyXH}ygYJ(**
 </p>

 Final Key: 
 ```
 ,(V6T.xu 'boyXH}ygYJ(
 ```

Encryption
--------

With generated key and plaintext, the encryption process started. It can divided into two parts:
* Base-Format Encryption
* Padding <br>

Padding is done in 5 steps:
* Format length of encrypted string (C)
* Format length of generated key (K)
* Key-triggered-reversible-shuffle
* Hexadecimal-conversion
* Randomizing with CC and EA characters

**Example:** <br>

 We got:<p align = "center">
  Generated Key (K) (21) = **,(V6T.xu 'boyXH}ygYJ(** <br>
  Message (M) (21) = **Hajee DanesH 26/10/19**
</p>

 Then:<p align = "center">
  Base-Format Encryption (C) (21) = __t+b=[N^x0.wY;, NL9*{a__ <br>
 </p>
 
 Padding:<p align = "center">
  Format length of encrypted string (C) (24) = __t+b=[N^x0.wY;, NL9*{a~~~__ <br>
  Format length of generated key (K) (24) = **,(V6T.xu 'boyXH}ygYJ(,(V** <br>
  Key-triggered-reversible shuffle (C) = __~,t~~L=a0Y{N[+w.;x9b^*N__ <br>
  Hexadecimal-conversion = **7E2C747E7E4C3D6130597B4E5B2B772E3B7839625E2A4E20** <br>
  Randomizing with CC and EA = **082C7498034C3D6130597B4E5B2B772E3B7839625E2A4E20**
 </p>
 
 Final Encrypted Result:  
 ```
 082C7498034C3D6130597B4E5B2B772E3B7839625E2A4E20
 ```

Decryption
-------

Decryption process divides in two parts:
* Normalizing of Encrypted String (C)
* Decryption in Base-Format (M)

> Key Generation is always the first step in both Encryption and Decryption. <br>

Normalizing of encrypted string is done with 5 steps:
* Character seperation of CC and EA
* Base conversion (C)
* Format generated key (K)
* Key-Triggered-reversible shuffle
* Fix Length of encrypted string

**Example:** <br>

 We got:<p align = "center">
  Generated Key (K) (21) = **,(V6T.xu 'boyXH}ygYJ(** <br>
  Ciphertext (C) (24) = **082C7498034C3D6130597B4E5B2B772E3B7839625E2A4E20** <br>
</p>

Decryption:<p align = "center">
  Character seperation of CC and EA = __7E2C747E7E4C3D6130597B4E5B2B772E3B7839625E2A4E20__ <br>
  Base conversion (C) = __~,t~~L=a0Y{N[+w.;x9b^*N__ <br>
  Format generated key (K) = __,(V6T.xu 'boyXH}ygYJ(,(V__ <br>
  Key-triggered-reversible shuffle (C) (24) = __t+b=[N^x0.wY;, NL9*{a~~~__ <br>
  Fix length (C) (21) = __t+b=[N^x0.wY;, NL9*{a__ <br>
  Decryption in base-format (M) = **Hajee DanesH 26/10/19**
 </p>
 
 Final Decrypted Result:  
 ```
 Hajee DanesH 26/10/19
 ```
 
Advantages
-------
* Key used in this process meets standard password requirements
* Slightest change of the key results a completely different encrypted string
* Encrypted string is in hexadecimal format ranges from ASCII 0-255
* Encrypted string is a multiplication of 16 in hex. 
* RSA encryption is a way of key-distribution of BSK cipher. Thus removes the drawbacks of symmetric-key cipher.

:copyright:Sazzad-Saju <p align = "center">
 END OF DOCUMENT :smile:
</p>
