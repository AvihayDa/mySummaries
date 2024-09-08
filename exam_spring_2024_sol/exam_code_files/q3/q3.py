import os
import json
import sys

# when run as a script, pass the directory path "json_files_dir" as an argument
# there is 3 json files in the directory, each file contains a student's name, exam grade and homework grades

class Student:
    def __init__(self, name : str, exam_grade : int, hw_grades : list):
        self.name = name
        self.exam_grade = exam_grade
        self.hw_grades = hw_grades.copy()
        
    def get_final_grade(self, exam_weight : float, hw_weight : list):
        examf = self.exam_grade * exam_weight
        hwf = sum([x*y for x,y in zip(self.hw_grades, hw_weight)])
        return examf + hwf
    

x = Student("Daniel", 90, [100, 80, 90])

def load_student_from_path(path : str):
    with open(path, 'r') as f:
        data = json.load(f)
    return Student(data['name'], data['exam_grade'], data['hw_grades'])

def print_students_in_dir(input_dir_path : str, exam_weight : float, hw_weight : list):
    fileList = os.listdir(input_dir_path)
    for file in fileList:
        if file.endswith(".json"):
            student = load_student_from_path(input_dir_path + os.sep + file)
            name = student.name + ":"
            print(name, student.get_final_grade(exam_weight, hw_weight))


exam_weight = 0.5 # global variables, same as the one in the test example
hw_weight = [0.1, 0.15, 0.25]

def main(path : str):
    try:
        print_students_in_dir(path, exam_weight, hw_weight)
    except :
        print("An error has occurred", file=sys.stderr)


if __name__ == "__main__":
    main(sys.argv[1])