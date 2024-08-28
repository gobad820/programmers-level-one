import os
import re
from datetime import datetime

# README 파일 경로
README_PATH = 'README.md'

# solutions 디렉토리 경로
SOLUTIONS_DIR = 'solutions'

def update_readme():
    with open(README_PATH, 'r', encoding='utf-8') as file:
        content = file.read()

    # 문제 목록 섹션 찾기
    problem_list_section = re.search(r'(## 문제 목록\n\n\| 문제 이름 \| 완료 여부 \| 날짜 \|[\s\S]+?\n)(\*\*현재 진행 상황)', content)

    if not problem_list_section:
        print("문제 목록 섹션을 찾을 수 없습니다.")
        return

    problem_list = problem_list_section.group(1)
    lines = problem_list.splitlines()

    # 각 문제에 대한 상태 업데이트
    new_lines = [lines[0]]  # 헤더
    for line in lines[1:]:
        match = re.match(r'\| \[(.+)\] \| ([^\|]+) \| ([^\|]+) \|', line)
        if match:
            problem_name = match.group(1)
            is_completed = match.group(2)
            date_completed = match.group(3)

            # 해당 문제에 대한 솔루션 파일 경로
            solution_dir = os.path.join(SOLUTIONS_DIR, problem_name)
            solution_files = [f for f in os.listdir(solution_dir) if f.endswith('.cc')] if os.path.exists(solution_dir) else []

            if solution_files:
                is_completed = '✅'
                date_completed = datetime.now().strftime('%Y/%m/%d')
                problem_link = f'[링크](solutions/{problem_name}/{solution_files[0]})'
            else:
                is_completed = '-'
                date_completed = '-'
                problem_link = problem_name

            new_line = f'| {problem_link} | {is_completed} | {date_completed} |'
            new_lines.append(new_line)
        else:
            new_lines.append(line)

    # 업데이트된 내용을 삽입
    updated_content = content.replace(problem_list_section.group(1), '\n'.join(new_lines) + '\n')
    with open(README_PATH, 'w', encoding='utf-8') as file:
        file.write(updated_content)

if __name__ == "__main__":
    update_readme()
