#!/bin/bash
# Forçar ponto decimal em todo o ambiente do script
export LC_ALL=C
export LANG=C
export LC_NUMERIC=C

FILE="../tmp/controller.log"

if [ ! -s "$FILE" ]; then
    echo "Log file not found or empty!"
    exit 1
fi

awk -F'|' '
{
    user = $1
    gsub(/^ +| +$/,"", user)  # remove espaços


    # Extrair apenas o numero do campo 3 (turnaround)
    # Procuramos por digitos seguidos de ponto e mais digitos
    match($3, /[0-9]+\.[0-9]+/); 
    t_val = substr($3, RSTART, RLENGTH);
    
    # Extrair apenas o numero do campo 4 (response)
    match($4, /[0-9]+\.[0-9]+/); 
    r_val = substr($4, RSTART, RLENGTH);

    if (t_val != "" && r_val != "") {
        sum_t += t_val;
        sum_r += r_val;
        count++;

        sum_t_user[user] += t_val;
        sum_r_user[user] += r_val;  #Basicamente aqui só cria um array em q o indice é o user id e faz o mesmo que faz em cima.
        count_user[user]++;
    }
}
END {
    #Média total
    if (count > 0) {
        printf "Average Turnaround: %.3f ms\n", sum_t/count;
        printf "Average Response: %.3f ms\n", sum_r/count;
    } else {
        print "Error: No numeric data could be parsed.";
        print "Check if the log format matches: user-id|command-id|turnaround X.XXX|response Y.YYY";
        }
    
    # Média por user
    printf "=== POR USER ===\n";    
    for (u in sum_t_user) {
        if (count_user[u] > 0) {
            printf "User %s: Avg Turnaround = %.3f ms, Avg Response = %.3f ms\n",
                u, sum_t_user[u]/count_user[u], sum_r_user[u]/count_user[u];
        } else {
            printf "User %s: No valid data\n", u
        }
    }
}' "$FILE"