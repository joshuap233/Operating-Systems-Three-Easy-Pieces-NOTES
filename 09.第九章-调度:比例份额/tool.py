import re


def compute_modulo(s: str, m: int):
    """
        example:
        s = \"\"\"
            Random 511275
            Random 404934
            Random 783799
            Random 303313
            Random 476597
            Random 583382
            Random 908113
            Random 504687
            Random 281838
            Random 755804
            Random 618369
            Random 250506
        \"\"\"
        compute_modulo(s,100)
    """
    s_number = re.findall(r'(\d+)\n', s)
    res = list(map(lambda x: int(x) % m, s_number))
    print(res)
    return res
