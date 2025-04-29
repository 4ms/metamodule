import json

def read_json_symbols(infile):
    with open(infile, "r") as f:
        table = json.load(f)
    if isinstance(table, dict):
        return table.keys()
    else:
        return table

def read_textfile_symbols(infile):
    with open(infile, "r") as f:
        needed_syms = [line.rstrip() for line in f]
    return needed_syms

def read_symbol_list(infile):
    if str(infile).endswith(".json"):
        needed_syms = read_json_symbols(infile)
    else:
        needed_syms = read_textfile_symbols(infile)

    needed_syms = list(set(needed_syms))
    return needed_syms

def write_yaml(outfile, syms):
    data = "Symbols:\n"
    for sym, addr in syms.items():
        data += f"  - Name: {sym}\n"
        # data += f"    Hash: {elfhash(sym)}\n"
        data += f"    Addr: {hex(addr)}\n"

    with open(outfile, "w") as f:
        f.write(data)

        # Pad so that data size is aligned to 4 bytes
        padding = len(data) % 4
        f.write("\x00" * padding)
        # Add an additional padding of 4 bytes
        f.write("\x00" * 4)

def write_json(outfile, syms):
    data = json.dumps(syms)
    with open(outfile, "w") as f:
        f.write(data)

def write_text(outfile, syms):
    with open(outfile, "w") as f:
        for sym in syms:
            f.write(f"{sym}\n")

