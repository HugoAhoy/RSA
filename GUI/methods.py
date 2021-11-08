from tkinter.filedialog import askopenfilename, asksaveasfilename
from pathlib import Path

def generate_key(proc, combo, pub_n_label, pub_e_label, priv_label):
    key_length = int(combo.get()[4:])
    proc.stdin.write(b"keygen\n")
    proc.stdin.write((str(key_length)+'\n').encode())
    proc.stdin.flush()
    public_n = proc.stdout.readline().decode().strip()
    public_e = proc.stdout.readline().decode().strip()
    private_d = proc.stdout.readline().decode().strip()
    print(public_n)
    print(public_e)
    print(private_d)
    pub_n_label.config(text=Decimal2Hex(public_n))
    pub_e_label.config(text=Decimal2Hex(public_e))
    priv_label.config(text=Decimal2Hex(private_d))

# l 是二进制长度
def pad_hex(a, l):
    a.lstrip("0x")
    hex_l = l >> 2
    len_to_pad = (hex_l - len(a)%hex_l)
    if len_to_pad == hex_l:
        len_to_pad = 0
    return '0'*len_to_pad+a

# l 是二进制长度
def split_hex(a, l):
    a = pad_hex(a, l)
    hex_l = l>>2
    parts = len(a) // hex_l
    splited_hex = [a[i*hex_l:(i+1)*hex_l] for i in range(parts)]
    return splited_hex

# str-->hex-->int-->encrypt-->int-->hex
def encrypt(proc, public_e, public_n, contents, ciphertext):
    ciphers = []
    pub_e = public_e["text"].lstrip('0x').strip()
    pub_n = public_n["text"].lstrip('0x').strip()
    key_len = len(pub_n["text"])*4
    plain = contents.get("1.0","end")[:-1]
    plain_hex = plain.encode().hex()

    splited_hex = split_hex(c_hex, key_len>>1)
    part_len = len(splited_hex)
    proc.stdin.write(b"encrypt\n")
    proc.stdin.write((str(int(pub_e,16))+'\n').encode())
    proc.stdin.write((str(int(pub_n,16))+'\n').encode())
    proc.stdin.write((str(part_len)+'\n').encode())
    proc.stdin.flush()
    for content in splited_hex:
        proc.stdin.write((str(int(content,16))+'\n').encode())
        proc.stdin.flush()
        encrypted = proc.stdout.readline().decode().strip()
        ciphers.append('0x'+pad_hex(hex(encrypted).lstrip('0x'),key_len))
    # print(ciphers)
    ciphertext.delete("1.0","end")
    ciphertext.insert("insert", ' '.join(ciphers))
    print("ciphertext:",ciphertext.get("1.0","end")[:-1])


# hex-->int-->decrypt-->int-->hex-->str
def decrypt(proc, private_d, public_n, ciphertext, plaintext):
    plains = []
    priv_d = private_d["text"].lstrip('0x').strip()
    pub_n = public_n["text"].lstrip('0x').strip()
    key_len = len(pub_n["text"])*4
    cipher_hex = ciphertext.get("1.0","end")[:-1]
    splited_hex = ciphertext.split(' ')

    part_len = len(splited_hex)
    proc.stdin.write(b"decrypt\n")
    proc.stdin.write((str(int(priv_d,16))+'\n').encode())
    proc.stdin.write((str(int(pub_n,16))+'\n').encode())
    proc.stdin.write((str(part_len)+'\n').encode())
    proc.stdin.flush()
    first = True
    for cipher in splited_hex:
        content = int(cipher.lstrip('0x'), 16)
        proc.stdin.write((str(content)+'\n').encode())
        proc.stdin.flush()
        decrypted = proc.stdout.readline().decode().strip()
        if first:
            plains.append(hex(decrypted).lstrip('0x'))
            first = False
        else:
            plains.append(pad_hex(hex(decrypted).lstrip('0x'), key_len>>1))
    # print(plains)
    plaintext.delete("1.0","end")
    plaintext.insert("insert", bytes.fromhex(''.join(plains)).decode())
    print("plaintext:",plaintext.get("1.0","end")[:-1])

def test_decrypt(ciphertext, plaintext):
    cipher = ciphertext.get("1.0","end")[:-1] # 总会多读一个\n [:-1]去掉多的\n
    plaintext.delete("1.0","end")
    plaintext.insert("insert", cipher.encode().hex())

def test_encrypt(plaintext, ciphertext):
    plain = plaintext.get("1.0","end")[:-1]
    ciphertext.delete("1.0","end")
    ciphertext.insert("insert", bytes.fromhex(plain).decode())

def Decimal2Hex(num_d):
    return hex(int(num_d))

def Decimal2Hex2Str(num_d):
    return bytes.fromhex(hex(int(num_d)).lstrip('0x')).decode()

def Hex2Decimal(num_h):
    return int(num_h,16)

def read_private_key(pub_n, priv_d):
    filename = askopenfilename()
    print(filename)
    with Path(filename).open('r') as f:
        pub_n.config(text=f.readline().strip())
        priv_d.config(text=f.readline().strip())

def read_public_key(pub_n, pub_e):
    filename = askopenfilename()
    print(filename)
    with Path(filename).open('r') as f:
        pub_n.config(text=f.readline().strip())
        pub_e.config(text=f.readline().strip())

def save_keys(pub_n, pub_e, priv_d):
    filename = asksaveasfilename()
    print(filename)
    filename = Path(filename)
    pub_filename = filename.with_name(filename.stem+".pub")
    priv_filename = filename
    with pub_filename.open('w') as f:
        f.write(pub_n["text"]+"\n")
        f.write(pub_e["text"]+"\n")
    with priv_filename.open('w') as f:
        f.write(pub_n["text"]+"\n")
        f.write(priv_d["text"]+"\n")
