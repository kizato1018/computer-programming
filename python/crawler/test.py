data = 0

class C:
    def __init__(self):
        return
    def a(self):
        global data
        data += 1
        print('in C: ', data)

print(data)

c1 = C()
c1.a()

print(data)