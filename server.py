from flask import Flask, request, send_from_directory
import subprocess
import os

app = Flask(__name__)

@app.route('/')
def home():
    return send_from_directory('.', 'index.html')

@app.route('/run', methods=['POST'])
def run_code():
    data = request.get_json()
    resume = data['resume']
    effort = data['effort']

    user_input = f"{resume.strip()}\n{effort.strip()}\n"

    # Absolute path to the main.c file
    main_c_path = "C:/Users/sprus/OneDrive/Desktop/Allnew/main.c"
    output_path = "C:/Users/sprus/OneDrive/Desktop/Allnew/main.out"

    # Compile the C code
    compile = subprocess.run(["gcc", main_c_path, "-o", output_path], capture_output=True)
    if compile.returncode != 0:
        return f"Compilation Error:\n{compile.stderr.decode()}"

    # Run the compiled program
    run = subprocess.run([output_path], input=user_input.encode(), capture_output=True)
    return run.stdout.decode()

if __name__ == '__main__':
    app.run(debug=True)
