from tkinter import *
from tkinter.ttk import *
from methods import *

from subprocess import Popen
from subprocess import PIPE

p = Popen("GUI/RSA.exe", stdin=PIPE, stdout=PIPE)

# 窗口生成
window = Tk()
window.title("RSA")
window.geometry("800x600")

# 标签页生成
tab = Notebook(window)
frame1 = Frame(tab)
tab1 = tab.add(frame1, text = "密钥生成")
 
frame2 = Frame(tab)
tab2 = tab.add(frame2, text = "加密")
 
frame3 = Frame(tab)
tab3 = tab.add(frame3, text = "解密")
 
tab.pack(padx=5,pady=5,expand = True, fill = BOTH)
# 设置选中tab1
tab.select(frame1)

# 密钥生成标签页元素
RSA_length = Label(frame1, text = "加密等级: ")
RSA_length.grid(column=1, row=0)

level_combo = Combobox(frame1)
level_combo['values'] = ("RSA-256","RSA-512","RSA-768","RSA-1024","RSA-2048")
level_combo.current(1)
level_combo.grid(column=2, row=0)

priv_label = Label(frame1, text="私钥D: ")
priv_label.grid(column=0, row=3)
priv_content =Label(frame1)
priv_content.grid(column=1, row=3)

pub_n_label = Label(frame1, text="公钥N: ")
pub_n_label.grid(column=0, row=5)
pub_n_content =Label(frame1)
pub_n_content.grid(column=1, row=5)

pub_e_label = Label(frame1, text="公钥E: ")
pub_e_label.grid(column=0, row=7)
pub_e_content =Label(frame1)
pub_e_content.grid(column=1, row=7)

gen_btn = Button(frame1, text="生成",command=lambda: generate_key(p,level_combo,pub_n_label,pub_e_label,priv_label))
gen_btn.grid(column=3, row=0)

save_btn = Button(frame1, text="保存",command=lambda: save_keys(pub_n_label,pub_e_label,priv_label))
save_btn.grid(column=4, row=0)

# 加密标签页元素
en_public_n_label = Label(frame2, text = "公钥N")
en_public_n_label.grid(column=0, row=0)

en_public_n_Content = Label(frame2)
en_public_n_Content.grid(column=0, row=1)

en_public_e_label = Label(frame2, text = "公钥E")
en_public_e_label.grid(column=0, row=2)

en_public_e_Content = Label(frame2)
en_public_e_Content.grid(column=0, row=3)

en_cwe_label = Label(frame2, text = "明文")
en_cwe_label.grid(column=0,row=4)
en_content_without_encrypt = Text(frame2, height=5)  # 创建文本框控件，并制定文本框的高度
en_content_without_encrypt.grid(column=3,row=4)

en_ce_label = Label(frame2, text = "密文")
en_ce_label.grid(column=0,row=5)
en_content_encrypt = Text(frame2, height=5)  # 创建文本框控件，并制定文本框的高度
en_content_encrypt.grid(column=3,row=5)

en_open_privkey_btn = Button(frame2, text="打开公钥",command=lambda: read_public_key(en_public_n_Content, en_public_e_Content))
en_open_privkey_btn.grid(column=3, row=0)

en_encrypt_btn = Button(frame2, text="加密")
en_encrypt_btn.grid(column=4, row=0)

# 解密标签页元素
de_public_n_label = Label(frame3, text = "公钥N")
de_public_n_label.grid(column=0, row=0)

de_public_n_Content = Label(frame3)
de_public_n_Content.grid(column=0, row=1)

de_priv_d_label = Label(frame3, text = "私钥D")
de_priv_d_label.grid(column=0, row=2)

de_priv_d_Content = Label(frame3)
de_priv_d_Content.grid(column=0, row=3)

de_cwe_label = Label(frame3, text = "明文")
de_cwe_label.grid(column=0,row=4)
de_content_without_encrypt = Text(frame3, height=5)  # 创建文本框控件，并制定文本框的高度
de_content_without_encrypt.grid(column=3,row=4)

de_ce_label = Label(frame3, text = "密文")
de_ce_label.grid(column=0,row=5)
de_content_encrypt = Text(frame3, height=5)  # 创建文本框控件，并制定文本框的高度
de_content_encrypt.grid(column=3,row=5)

de_open_privkey_btn = Button(frame3, text="打开私钥",command=lambda: read_private_key(de_public_n_Content, de_priv_d_Content))
de_open_privkey_btn.grid(column=3, row=0)

de_encrypt_btn = Button(frame3, text="解密")
de_encrypt_btn.grid(column=4, row=0)

window.mainloop()

