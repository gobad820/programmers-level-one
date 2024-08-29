import os
import re
from datetime import datetime
from urllib.parse import quote

README_PATH = 'README.md'
SOLUTIONS_DIR = 'solutions'

def update_readme():
    with open(README_PATH, 'r', encoding='utf-8') as file:
        content = file.read()

    problem_list_section = re.search(r'(## 문제 목록\s*\n+\s*\|[^|]+\|[^|]+\|[^|]+\|[\s\S]+?)(?=\n##|\Z)', content)

    if not problem_list_section:
        print("문제 목록 섹션을 찾을 수 없습니다.")
        return

    problem_list = problem_list_section.group(1)
    lines = problem_list.splitlines()

    new_lines = [lines[0], lines[1]]  # 헤더와 구분선 유지
    for line in lines[2:]:
        match = re.match(r'\|\s*([^|]+)\s*\|\s*([^|]+)\s*\|\s*([^|]+)\s*\|', line)
        if match:
            problem_name = match.group(1).strip()
            current_status = match.group(2).strip()
            current_date = match.group(3).strip()

            solution_dir = os.path.join(SOLUTIONS_DIR, problem_name)
            solution_files = [f for f in os.listdir(solution_dir) if f.endswith('.cc')] if os.path.exists(solution_dir) else []

            if solution_files:
                encoded_problem_name = quote(problem_name)
                encoded_file_name = quote(solution_files[0])
                problem_link = f'[{problem_name}](https://github.com/gobad820/programmers-level-one/blob/main/solutions/{encoded_problem_name}/{encoded_file_name})'
                is_completed = '✅'
                date_completed = datetime.now().strftime('%Y/%m/%d')
            else:
                problem_link = problem_name
                is_completed = current_status if current_status != '-' else '-'
                date_completed = current_date if current_date != '-' else '-'

            new_line = f'| {problem_link} | {is_completed} | {date_completed} |'
            new_lines.append(new_line)
        else:
            new_lines.append(line)

    updated_content = content.replace(problem_list_section.group(0), '\n'.join(new_lines))

    with open(README_PATH, 'w', encoding='utf-8') as file:
        file.write(updated_content)

if __name__ == "__main__":
    update_readme()