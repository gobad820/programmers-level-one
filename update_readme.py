import os
import re
from datetime import datetime
from github import Github

def get_problem_info(directory):
    problems = {}
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith('.cc'):
                problem_name = os.path.basename(os.path.dirname(os.path.join(root, file)))
                file_path = os.path.relpath(os.path.join(root, file), directory)
                problems[problem_name] = file_path
                print(f"Found problem: {problem_name} at {file_path}")  # 디버깅용
    return problems

def update_readme(problems):
    with open('README.md', 'r', encoding='utf-8') as f:
        content = f.read()

    table_pattern = r'\| 문제 이름.*?\n(.*?)\n\n'
    table_content = re.search(table_pattern, content, re.DOTALL)

    if table_content:
        lines = table_content.group(1).split('\n')
        updated_lines = []
        completed_count = 0
        total_count = len(lines)

        for line in lines:
            match = re.search(r'\| \[(.*?)\].*?\| (.*?) \|', line)
            if match:
                problem_name, status = match.groups()
                problem_key = problem_name.replace(' ', '')  # 공백 제거
                if problem_key in problems:
                    file_path = problems[problem_key]
                    updated_line = f"| [{problem_name}](solutions/{file_path}) | ✅ | {datetime.now().strftime('%Y/%m/%d')} |"
                    completed_count += 1
                    print(f"Updating line: {updated_line}")  # 디버깅용
                elif status.strip() == '✅':
                    completed_count += 1
                    updated_line = line
                else:
                    updated_line = f"| [{problem_name}] | - | - |"
            else:
                updated_line = line
            updated_lines.append(updated_line)

        new_table_content = '\n'.join(updated_lines)
        new_content = re.sub(table_pattern, f'| 문제 이름 | 완료 여부 | 날짜 |\n{new_table_content}\n\n', content, flags=re.DOTALL)

        progress = f"**현재 진행 상황: {completed_count}/{total_count} ({completed_count/total_count*100:.2f}%)**\n\n"
        new_content = re.sub(r'\*\*현재 진행 상황:.*?\*\*\n\n', progress, new_content, flags=re.DOTALL)

        with open('README.md', 'w', encoding='utf-8') as f:
            f.write(new_content)

if __name__ == "__main__":
    g = Github(os.environ['GITHUB_TOKEN'])
    repo = g.get_repo(os.environ['GITHUB_REPOSITORY'])
    problems = get_problem_info('solutions')
    print(f"Found problems: {problems}")  # 디버깅용
    update_readme(problems)