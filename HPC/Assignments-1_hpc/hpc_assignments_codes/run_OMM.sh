threads_number=(2 4 6 8 10 12 14 16)
matrix_size=(512 1024 2048)
choice_user=(1 2)
block_size=1

#  Matrix Size Iteration
for size in "${matrix_size[@]}"; do
    # Threads Iteration
    for threads in "${threads_number[@]}";  do
        # Power Iterartion
        for ((pow = 2; pow <= 16; pow++)); do
          # User Choice Iteration
          for choice in "${choice_user[@]}";  do 
            ./Assignment1 $threads $size $pow $block_size $choice
          done
        done
    done
done






