import re

s = """
  VA  0: 0x0000007a (decimal:  122) --> PA or segmentation violation?
  VA  1: 0x00000079 (decimal:  121) --> PA or segmentation violation?
  VA  2: 0x00000007 (decimal:    7) --> PA or segmentation violation?
  VA  3: 0x0000000a (decimal:   10) --> PA or segmentation violation?
  VA  4: 0x0000006a (decimal:  106) --> PA or segmentation violation?
"""


# 提取地址并计算所处的段,
# addr_space 为地址空间大小
def seg(addr_space: int, s: str) -> None:
    l = addr_space.bit_length()

    def get_seg(addr: str) -> int:
        return 0 if addr.startswith('00') else 1

    def get_bin(addr: str) -> str:
        addr = int(addr)
        return '0' * (l - addr.bit_length()) + bin(addr)[2:]

    ads = re.findall(r'\b(\d*)\)', s)

    bin_ads = [get_bin(ad) for ad in ads]
    print([get_seg(addr) for addr in bin_ads])


seg(128, s)
