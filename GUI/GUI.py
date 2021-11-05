from tkinter import *
from tkinter.ttk import *
from methods import *

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

gen_btn = Button(frame1, text="生成",command=lambda: generate_key(level_combo, priv_content, pub_n_content, pub_e_content))
gen_btn.grid(column=3, row=0)

# 加密标签页元素
public_n_label = Label(frame2, text = "公钥N")
public_n_label.grid(column=0, row=0)

public_n_Content = Label(frame2)
public_n_Content.grid(column=0, row=1)

public_e_label = Label(frame2, text = "公钥E")
public_e_label.grid(column=0, row=2)

public_e_Content = Label(frame2)
public_e_Content.grid(column=0, row=3)

cwe_label = Label(frame2, text = "明文")
cwe_label.grid(column=0,row=4)
content_without_encrypt = Text(frame2, height=5)  # 创建文本框控件，并制定文本框的高度
content_without_encrypt.grid(column=3,row=4)

ce_label = Label(frame2, text = "密文")
ce_label.grid(column=0,row=5)
content_encrypt = Text(frame2, height=5)  # 创建文本框控件，并制定文本框的高度
content_encrypt.grid(column=3,row=5)

encrypt_btn = Button(frame2, text="加密")
encrypt_btn.grid(column=3, row=0)

window.mainloop()

