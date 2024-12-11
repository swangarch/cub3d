#!/bin/bash

# 确保脚本在当前目录执行 ./cub3D
# 以及 maps/bad 路径正确

MAP_DIR="maps/error"
EXECUTABLE="./cub3D"

# 检查 maps/bad 是否存在
if [[ ! -d "$MAP_DIR" ]]; then
    echo "Error: Directory $MAP_DIR does not exist."
    exit 1
fi

# 检查 ./cub3D 是否可执行
if [[ ! -x "$EXECUTABLE" ]]; then
    echo "Error: $EXECUTABLE is not executable or does not exist."
    exit 1
fi

# 遍历 maps/bad 文件夹中的所有文件
for map_file in "$MAP_DIR"/*; do
    if [[ -f "$map_file" ]]; then
        echo "Executing $EXECUTABLE with argument: $map_file under Valgrind"

        # 使用 valgrind 执行 cub3D，捕获输出结果
        output=$(valgrind --leak-check=full --error-exitcode=1 $EXECUTABLE "$map_file" 2>&1)

        # 检查输出是否包含 "Error"
        if ! echo "$output" | grep -q "Error"; then
            echo "No 'Error' found in output for: $map_file"
        else
            echo "Output contains 'Error' for: $map_file"
        fi

        # 检查 Valgrind 是否返回内存问题
        if [[ $? -ne 0 ]]; then
            echo "Valgrind detected issues for: $map_file"
        else
            echo "No Valgrind issues for: $map_file"
        fi

    else
        echo "Skipping non-regular file: $map_file"
    fi
done

