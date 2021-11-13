import subprocess
import csv

tc = [25, 50, 100, 250, 1000]
tp = [25, 50, 100, 250, 1000]
qs = [25, 50, 100]

with open("benchmarks/results.csv", 'w', newline='') as f:
    writer = csv.writer(f, delimiter=',')
    writer.writerow(["Producer Sleep Range","Consumer Sleep Range","Queue Size","Items Produced","Items Consumed","Producers Halted","Consumers Halted"])
    for c in tc:
        for p in tp:
            for s in qs:
                compile = f"g++ src/main.cpp src/BoundedBufferQueue.cpp -o src/main -I include/"
                run = f"./src/main -tc={c} -tp={p} -qs={s} > benchmarks/tc{c}tp{p}qs{s}.txt"
                subprocess.run(compile.split(' '))
                result = subprocess.Popen(run.split(' '),
                        stdout=subprocess.PIPE, 
                        stderr=subprocess.PIPE)
                stdout, stderr = result.communicate()
                stdout = stdout.decode('utf-8')[:-1]
                writer.writerow([p,c,s] + stdout.split(','))
