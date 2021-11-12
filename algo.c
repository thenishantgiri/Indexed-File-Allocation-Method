#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef char String[32]; // There is a limit on length of file name

// Let us take some convenient values for total size of disk, size of a block, and the maximum no of files.
// These can be changed.
#define TOTAL_SIZE_KiB (64)
#define BLOCK_SIZE_KiB (1)
#define MAX_FILES (64) // (TOTAL_SIZE_KiB / BLOCK_SIZE_KiB) // 64 index blocks; each file 0 KiB
#define MAX_BLOCKS (64) // (TOTAL_SIZE_KiB / BLOCK_SIZE_KiB) 

typedef struct Block
{
    bool occupied; // does this block belon to any file
    int* arr; // if this block is an index block, 
    // arr stores indices of all storage blocks belonging to the file

    int arr_size; 
    // occupied = true and arr = NULL means block is used for storage
    // occupied = true and arr != NULL means block is used as index block
}Block;

// disk is a global array variable indicating 
// that the hard disk is divided into MAX_BLOCKS blocks
Block disk[MAX_BLOCKS]; 
int nf_occupied_blocks = 0;

void print_disk() // prints out the list of occupied blocks
{
    if (!nf_occupied_blocks)
    {
        printf("Out of %d blocks, none are occupied. \n", MAX_BLOCKS);
        return;
    }
    printf("Out of %d blocks, these are occupied: \n", MAX_BLOCKS);
    for (int i = 0; i < MAX_BLOCKS; ++i)
    {
        if (disk[i].occupied)
            printf("%d ", i);
    }
    printf("\n");
}

int find_first_unoccupied_block(int start) 
{
    // iteration will start at index `start` and go ahead till the last index
    // if all of these blocks are occupied, 
    // then iteration will continue from 0 to `start` - 1
    for (int i = start; i < MAX_BLOCKS; ++i)
    {
        if (disk[i].occupied == false)
        {
            return i;
        }
    }
    for (int i = 0; i < start; ++i)
    {
        if (disk[i].occupied == false)
        {
            return i;
        }
    }
    return -1; // all blocks are occupied
}

typedef struct File
{
    String name; // file name
    int size_KiB; // size of file in kibibytes (1KiB = 1024B)
    Block* index_block; // pointer to the index block
}File;

typedef struct Directory
{
    File* files; // directory stores a list of files
    int nf_files; // total no. of files in directory
}Directory;

void initialize_dir(Directory* dir) // constructor
{
    // allocate memory to `files`
    // `files` can now be treated as an array of MAX_FILES files
    dir->files = calloc(sizeof(File), MAX_FILES); 
    dir->nf_files = 0; // initially there are no files in directory
}

void destroy_dir(Directory* dir) // destructor
{
    free(dir->files);
}

void add_file(Directory* dir) // read file details, allocate file and add file to directory
// also lists out which blocks which allocated for what
{
    File new_file;
    // read file name and size
    printf("File name and file size: ");
    scanf("%s %d", new_file.name, &new_file.size_KiB);

    // check whether there is enough space for the new file
    // the new file will require one index block 
    // and ceiling(file size / block size) storage blocks
    int nf_storage_blocks = ceil(new_file.size_KiB / (BLOCK_SIZE_KiB * 1.0));
    if (nf_storage_blocks + 1 > MAX_BLOCKS - nf_occupied_blocks)
    {
        printf("Not enough disk space.\n");
        return;
    }

    // allocate the index block
    // using random `start` so that occupied blocks are spread 
    // throghout the disk instead of being concentrated at the beginning
    int index_block_no = find_first_unoccupied_block(rand() % MAX_BLOCKS);
    printf("Index block at position %d.\n", index_block_no);
    if (index_block_no == -1) 
    {   // Shouldn't reach here because we already checked if there is enough disk space
        printf("No unoccupied blocks for index.\n");
        return;
    }

    new_file.index_block = &disk[index_block_no];
    new_file.index_block->occupied = true;
    nf_occupied_blocks ++;

    // give heap memory to index_block's `arr` variable
    new_file.index_block->arr = calloc(sizeof(int), MAX_BLOCKS);
    new_file.index_block->arr_size = 0;

    // allocate each storage block and add it to the index_block's arr
    for (int i = 0; i < nf_storage_blocks; ++i)
    {
        int block_no = find_first_unoccupied_block(rand() % MAX_BLOCKS);
        if (block_no == -1) // Shouldn't reach here; same reason as before
        {
            printf("No unoccupied blocks for storage.\n");
            return;
        }
        printf("Block %d at position %d.\n", i, block_no);

        disk[block_no].occupied = true;
        nf_occupied_blocks ++;
        new_file.index_block->arr[new_file.index_block->arr_size ++] = block_no;
    }

    // add new file to directory
    dir->files[dir->nf_files++] = new_file;
}

// read file name and index to storage block to seek 
// and print out which block no that corresponds to on the disk
void seek_file(Directory* dir) 
{
    String item; int block_no;
    // printf("File name; block no. to seek: ")
    scanf("%s %d", item, &block_no);

    // check if file exists
    int position = -1;
    for (int i = 0; i < dir->nf_files; ++i)
    {
        if (strcmp(dir->files[i].name, item) == 0)
        {
            position = i;
            break;
        }
    }
    if (position == -1)
    {
        printf("File not found.\n");
        return;
    }

    // find block no on disk
    // check if given block no exceeds no of storage block owned by file
    File* file = &dir->files[position];
    if (block_no < file->index_block->arr_size) 
    {
        int block_no_on_disk = file->index_block->arr[block_no];
        printf("The block no. on disk is %d.\n", block_no_on_disk);
    }
    else
    {
        printf("File does not have block %d.\n", block_no);
    }
}

// delete a file from the directory and deallocate all of its blocks
void delete_file(Directory* dir)
{
    String item;
    // printf("File name: ");
    scanf("%s", item);

    // does this file exist
    int position = -1;
    for (int i = 0; i < dir->nf_files; ++i)
    {
        if (strcmp(dir->files[i].name, item) == 0)
        {
            position = i;
            break;
        }
    }
    if (position == -1)
    {
        printf("File not found.\n");
        return;
    }

    // mark all storage blocks as unoccupied
    File* file = &dir->files[position];
    for (int i = 0; i < file->index_block->arr_size; ++i)
    {
        disk[file->index_block->arr[i]].occupied = false;
        nf_occupied_blocks --;
    }

    // mark index block as unoccupied
    file->index_block->occupied = false;
    nf_occupied_blocks --;
    free(file->index_block->arr); // free index block's array
    file->index_block->arr = NULL; // it's good practice to assign it null after freeing
    file->index_block->arr_size = 0;

    // remove file from directory
    for (int i = position; i < MAX_FILES - 1; ++i)
    {
        dir->files[i] = dir->files[i + 1];
    }
    dir->nf_files --;
}

// list names of all files in directory
void list_files(Directory* dir)
{
    bool nonempty = false;
    for(int i = 0; i < dir->nf_files; ++i)
    {
        nonempty = true;
        printf("%s\n", dir->files[i].name);
    }
    if (!nonempty)
    {
        printf("Empty Directory.\n");
    }
}

int main(int argc, char const *argv[])
{
    Directory dir;
    initialize_dir(&dir);
    String command;
    do
    {
        printf(">>> "); // chevron prompt
        scanf("%s", command);

        // call function corresponding to command
        if (strcmp(command, "add") == 0) add_file(&dir);
        else if (strcmp(command, "del") == 0) delete_file(&dir);
        else if (strcmp(command, "list") == 0) list_files(&dir);
        else if (strcmp(command, "seek") == 0) seek_file(&dir);
        else if (strcmp(command, "disk") == 0) print_disk();
        else break; // any invalid command exits the program

        printf("\n");
    }
    while(true);

    destroy_dir(&dir); // free up allocated memory

    return 0;
}