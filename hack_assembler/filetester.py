def cmp_files(f1,f2):
    for l1,l2 in zip(f1,f2):
        if l1 != l2:
            return False
    return True


with open("addtest.hack","r") as f1:
    with open("addtest2.hack", "r") as f2:
        print(cmp_files(f1,f2))
