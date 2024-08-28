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
    problem_list_section = re.search(r'(## 문제 목록\n\| 문제 이름\s+\| 완료 여부\s+\| 날짜 \|[\s\S]+?)(\*\*현재 진행 상황)', content)

    if not problem_list_section:
        print("문제 목록 섹션을 찾을 수 없습니다.")
        return

    problem_list = problem_list_section.group(1)
    lines = problem_list.splitlines()

    # 각 문제에 대한 상태 업데이트
    new_lines = [lines[0]]  # 헤더
    updated_any = False  # 업데이트된 내용이 있는지 확인하는 플래그

    for line in lines[1:]:
        match = re.match(r'\| (.+?) \| ([^\|]+) \| ([^\|]+) \|', line)
        if match:
            problem_name = match.group(1).strip()
            is_completed = match.group(2).strip()
            date_completed = match.group(3).strip()

            # 해당 문제에 대한 솔루션 파일 경로
            solution_dir = os.path.join(SOLUTIONS_DIR, problem_name)
            solution_files = [f for f in os.listdir(solution_dir) if f.endswith('.cc')] if os.path.exists(solution_dir) else []

            if solution_files:
                print(f"Solution found for {problem_name}: {solution_files[0]}")
                is_completed = '✅'
                date_completed = datetime.now().strftime('%Y/%m/%d')
                problem_link = f'[{problem_name}](solutions/{problem_name}/{solution_files[0]})'
                updated_any = True
            else:
                print(f"No solution found for {problem_name}")
                problem_link = problem_name

            new_line = f'| {problem_link} | {is_completed} | {date_completed} |'
            new_lines.append(new_line)
        else:
            new_lines.append(line)

    # 업데이트된 내용을 삽입
    updated_content = content.replace(problem_list_section.group(1), '\n'.join(new_lines) + '\n')

    if updated_any:
        with open(README_PATH, 'w', encoding='utf-8') as file:
            file.write(updated_content)
        print("README.md 파일이 업데이트되었습니다.")
    else:
        print("업데이트할 내용이 없습니다.")

if __name__ == "__main__":
    update_readme()
