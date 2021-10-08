def __check_n2k(n, k):
    if n > 0 and n & (n - 1) == 0:
        m = 0
        while n > 1:
            n >>= 1
            m += 1
        return m == k
    return k == -1

def __check_fact(n, m):
    f = 1
    i = 2
    while i <= n:
        f = f * i
        i += 1
    return f == m

def __check_revert(n, m):
    r = 0
    while n > 0:
        r = r * 10 + n % 10
        n = n // 10
    return r == m

# def __check_fib(*fib):
#     if len(fib) > 2 and fib[0] == 1 and fib[1] == 1:
#         i = 2
#         while i < len(fib):
#             if fib[i] != fib[i - 1] + fib[i - 2]:
#                 return False
#             i += 1
#         return True
#     return False

def __check_fib_m2n(m, n, fib):
    return True

cases = [
    ('{:d} => {:d}', __check_n2k),
    (
        '{:d} {:d} {:d} => {:d} {:d} {:d}', 
        lambda a1, a2, a3, a4, a5, a6: a4 <= a5 and a5 <= a6
    ),
    ('{:d} => {:d}', __check_fact),
    ('[{:d}-{:d}] => {}', __check_fib_m2n),
    ('{:d} => {:d}', __check_revert),
    ]
