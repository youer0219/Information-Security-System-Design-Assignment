import sys

def pkcs7_unpadding(data):
    # 获取最后一个字节的值，这个值表示填充的字节数
    padding_value = data[-1]
    # 解除填充
    return data[:-padding_value]

def main(input_file, output_file):
    try:
        # 读取输入文件
        with open(input_file, 'rb') as infile:
            padded_data = infile.read()
        
        # 解除PKCS#7填充
        unpadded_data = pkcs7_unpadding(padded_data)
        
        # 将解除填充后的数据写入输出文件
        with open(output_file, 'wb') as outfile:
            outfile.write(unpadded_data)

        print(f"解除填充成功！已将结果写入 '{output_file}'")

    except Exception as e:
        print(f"处理过程中出现错误: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("用法: python remove_pkcs7_padding.py <输入文件名> <输出文件名>")
        sys.exit(1)

    input_filename = sys.argv[1]
    output_filename = sys.argv[2]

    main(input_filename, output_filename)
