cases = [('{:d} + {:d} = {:d}', lambda a, b, c: (a + b) == c)]

# cases = [('{:d} {:d} => {:d} {:d}', lambda a, b, c, d: (a, b) == (d, c)),
#     ('{:d} => {:d}', lambda y, b: (y % 4 == 0 and y % 100 != 0 or y % 400 == 0) == b),
#     ('{:f} {:f} {:f} => {:d}', lambda a, b, dt, c: (a - b < dt and a - b > -dt) == c),
#     ('{:d} => {:d}', lambda n, b: not(n & 1) == b),
#     ('{:d} => {:d} {:d} {:d}', lambda n, n1, n2, n3: (n << 4) + n == n1 and n & 7 == n2 and n >> 4 == n3),
#     ('{:d} => {:d}', lambda n, b: (n > 0 and n & (n - 1) == 0) == b),
#     ('{:o} => {:o} {:o} {:o} {:o}', lambda m0, m1, m2, m3, m4: m1 == 0o600 and m2 == (m0 | 0o111) and m3 == (m0 | 0o200) and m4 == (m0 & ~0o22))]
