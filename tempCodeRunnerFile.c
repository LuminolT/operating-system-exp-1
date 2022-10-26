    int pid, *pint;
    sleep(5);
    // extern cleanup();
    for (int i = 0; i < 20; i++) {
        signal(i, cleanup());
    }

    msgqid = msgget(MSGKEY, 0777 | IPC_CREAT);

    while (1) {
        msgrcv(msgqid, &msg, 256, 1, 0);
        pint = (int *)msg.mtext;
        pid = *pint;
        printf("Server: receive from pid %d.\n", pid);
        msg.mtype = pid;
        *pint = getpid();
        msgsnd(msgqid, &msg, sizeof(int), 0);
        *pint = getppid();
        msgsnd(msgqid, &msg, sizeof(int), 0);
    }