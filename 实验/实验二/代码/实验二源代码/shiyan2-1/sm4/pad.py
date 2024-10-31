import sys

def pad_data(data, block_size=16):
    padding_length = block_size - (len(data) % block_size)
    if padding_length == 0:
        padding_length = block_size
    padding = bytes([padding_length] * padding_length)
    return data + padding

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 pad.py <input_file> <output_file>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]

    try:
        with open(input_file, 'rb') as f:
            data = f.read()

        padded_data = pad_data(data)

        with open(output_file, 'wb') as f:
            f.write(padded_data)

        print(f"Padded data written to {output_file}")
    except Exception as e:
        print(f"Error: {e}")
        sys.exit(1)
