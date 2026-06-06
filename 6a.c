#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

// Step 1: Define the message structure
// CRITICAL EXAM RULE: The first variable MUST be a long integer!
struct msg_buffer {
    long msg_type;
    char msg_text[100];
} message;

int main() {
    // Step 2: Create a message queue
    // IPC_PRIVATE automatically generates a unique key. 0666 gives read/write permissions.
    int msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);

    if (msgid < 0) {
        printf("Error: Message Queue creation failed.\n");
        return 1;
    }

    // Step 3: Fork to create Producer and Consumer processes
    pid_t pid = fork();

    if (pid < 0) {
        printf("Error: Fork failed.\n");
        return 1;
    } 
    else if (pid == 0) {
        // --- CHILD PROCESS (PRODUCER) ---
        
        printf("PRODUCER (Child): Enter a message to send: ");
        fgets(message.msg_text, 100, stdin); // Get user input
        
        // Remove the trailing newline character that fgets() adds
        message.msg_text[strcspn(message.msg_text, "\n")] = 0; 
        
        // Message type must be a positive number (> 0)
        message.msg_type = 1; 

        // Send the message: msgsnd(queue_id, &message_struct, text_size, flags)
        msgsnd(msgid, &message, sizeof(message.msg_text), 0);
        printf("PRODUCER (Child): Message successfully sent to the queue.\n");
    } 
    else {
        // --- PARENT PROCESS (CONSUMER) ---
        
        // Wait for the Producer (Child) to finish sending the message first
        wait(NULL); 
        
        // Receive the message: msgrcv(queue_id, &message_struct, text_size, message_type, flags)
        msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0);
        printf("\nCONSUMER (Parent): Message received -> \"%s\"\n", message.msg_text);

        // Destroy the message queue completely
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}