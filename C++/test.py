def studentList():
    slist = []

    while True:
        try:
            print("\n Thông tin sinh viên")
            name = input("Tên sinh viên: ")
            index = input("Mã số sinh viên: ")
            avg_str = input("Điểm trung bình: ")
            avg = float(avg_str)

            student = {
                'name': name,
                'index': index,
                'point': avg
            }

            slist.append(student);

            check = input("Thêm sinh viên? (y/n): ")
            if check.lower() != 'y':
                break
        except Exception as e:
            print(f"Thử lại")

    print("\n\n Danh sách học sinh có điểm trên 8.0")
    goodstudent = False
    for x in slist:
        if x['point'] >= 8.0:
            print(f"Tên: {x['name']}, Mã số: {x['index']}, Điểm: {x['point']}")
            goodstudent = True;

    if not goodstudent:
        print("Không có sinh viên nào có điểm trung bình từ 8.0 trở lên.")

    slist.sort(key = lambda x : x['point'], reverse = True)

    print("\n\n Danh sách sinh viên")
    for x in slist:
        print(f"Tên: {x['name']}, Mã số: {x['index']}, Điểm: {x['point']}")

if __name__ == "__main__":
    studentList()
