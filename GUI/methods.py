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
    pub_n_label.config(text=public_n)
    pub_e_label.config(text=public_e)
    priv_label.config(text=private_d)

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

def Decimal2Hex(num_d):
    return hex(int(num_d))

def Decimal2Hex2Str(num_d):
    return bytes.fromhex(hex(int(num_d)).lstrip('0x')).decode()

def Hex2Decimal(num_h):
    return int(num_h,16)