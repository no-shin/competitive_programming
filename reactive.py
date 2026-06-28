#reactive.py
#!/usr/bin/env python3
import subprocess, select, time, sys
def log(prefix, msg, start):
  print(f"[{time.time()-start:6.3f}] {prefix} {msg}")

judge_cmd = ["./judge"]
if len(sys.argv) >= 2:
    judge_cmd.append(sys.argv[1])

judge = subprocess.Popen(
  judge_cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
  text=True
)
solve = subprocess.Popen(
  ["./solve"], stdin=subprocess.PIPE, stdout=subprocess.PIPE,
  text=True
)
start = time.time()
try:
    while True:
    # 両方終わってたら終了
        if judge.poll() is not None and solve.poll() is not None:
            break
        ready, _, _ = select.select([judge.stdout,solve.stdout], [], [], None)
        if not ready:
            continue
        for r in ready:
            line = r.readline()
            if not line:
                continue
            line = line.strip()
            if r == judge.stdout:
                log("JUDGE→", line, start)
                solve.stdin.write(line + "\n")
                solve.stdin.flush()
            else:
                log("SOLVE→", line, start)
                judge.stdin.write(line + "\n")
                judge.stdin.flush()
except KeyboardInterrupt:
    print("Interrupted.")
finally:
    for proc in [judge, solve]:
        if proc.poll() is None:
            proc.terminate()
