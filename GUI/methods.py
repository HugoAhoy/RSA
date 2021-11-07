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

# str-->hex-->int-->encrypt-->int-->hex
def encrypt(proc, public_e, public_n, contents, label):
    if not isinstance(contents,list):
        contents = [contents]
    res = []
    part_len = len(contents)
    proc.stdin.write(b"encrypt\n")
    proc.stdin.write((str(public_e)+'\n').encode())
    proc.stdin.write((str(public_n)+'\n').encode())
    proc.stdin.write((str(part_len)+'\n').encode())
    proc.stdin.flush()
    for content in contents:
        content = Hex2Decimal(content.encode().hex())
        proc.stdin.write((str(content)+'\n').encode())
        proc.stdin.flush()
        encrypted = proc.stdout.readline().decode().strip()
        res.append(encrypted)
    res = map(Decimal2Hex, res)
    print(res)
    label.config(text=' '.join(res))

# hex-->int-->decrypt-->int-->hex-->str
def decrypt(proc, private_d, public_n, contents, label):
    if not isinstance(contents,list):
        contents = [contents]
    res = []
    part_len = len(contents)
    proc.stdin.write(b"decrypt\n")
    proc.stdin.write((str(private_d)+'\n').encode())
    proc.stdin.write((str(public_n)+'\n').encode())
    proc.stdin.write((str(part_len)+'\n').encode())
    proc.stdin.flush()
    for content in contents:
        content = int(content,16)
        proc.stdin.write((str(content)+'\n').encode())
        proc.stdin.flush()
        encrypted = proc.stdout.readline().decode().strip()
        res.append(encrypted)
    res = map(Decimal2Hex2Str, res)
    print(res)
    label.config(text=' '.join(res))

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
