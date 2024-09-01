import os
import re
from datetime import datetime
from urllib.parse import quote

README_PATH = 'README.md'
SOLUTIONS_DIR = 'solutions'

def update_readme():
    with open(README_PATH, 'r', encoding='utf-8') as file:
        content = file.read()

    problem_list_section = re.search(r'(##\s*📚\s*문제\s*목록\s*\n\s*\|[^\n]*\|[^\n]*\|[^\n]*\|\s*\n\s*\|[^\n]*\|[^\n]*\|[^\n]*\|\s*\n((?:\s*\|.*\|.*\|.*\|\s*\n)*))', content, re.DOTALL)

    if not problem_list_section:
        print("문제 목록 섹션을 찾을 수 없습니다. README.md 파일의 구조를 확인해주세요.")
        return

    problem_list = problem_list_section.group(2)
    lines = problem_list.splitlines()

    new_lines = []
    for line in lines:
        if '|' in line:  # 테이블의 행인 경우에만 처리
            match = re.match(r'\|\s*([^|]+)\s*\|\s*([^|]+)\s*\|\s*([^|]+)\s*\|', line)
            if match:
                problem_name = match.group(1).strip()
                current_status = match.group(2).strip()
                current_date = match.group(3).strip()

                solution_dir = os.path.join(SOLUTIONS_DIR, problem_name)
                review_file = os.path.join(solution_dir, 'review.md')

                if os.path.exists(review_file):
                    encoded_problem_name = quote(problem_name)
                    problem_link = f'[{problem_name}](https://github.com/gobad820/programmers-level-one/blob/main/solutions/{encoded_problem_name}/review.md)'
                    is_completed = '✅'
                    date_completed = datetime.now().strftime('%Y/%m/%d')
                else:
                    problem_link = problem_name
                    is_completed = current_status if current_status != '-' else '-'
                    date_completed = current_date if current_date != '-' else '-'

                new_line = f'| {problem_link} | {is_completed} | {date_completed} |'
                new_lines.append(new_line)
            else:
                new_lines.append(line)  # 매치되지 않은 행은 그대로 유지
        else:
            new_lines.append(line)  # 테이블이 아닌 행은 그대로 유지

    updated_content = content.replace(problem_list_section.group(2), '\n'.join(new_lines))

    with open(README_PATH, 'w', encoding='utf-8') as file:
        file.write(updated_content)

    print("README.md 파일이 성공적으로 업데이트되었습니다.")

if __name__ == "__main__":
    update_readme()