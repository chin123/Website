struct boot_entry{
	char be_name[32];
	unsigned int be_offset;
	unsigned int be_type;
	unsigned int be_size;
	unsigned int be_vsize;
	unsigned int be_extra0;
	unsigned int be_extra1;
	unsigned int be_extra2;
	unsigned int be_extra3;
};

struct boot_dir{
	struct boot_entry bd_entry[64];
};

#define BE_TYPE_NONE 0
#define BE_TYPE_DIRECTORY 1
#define BE_TYPE_BOOTSTRAP 2
#define BE_TYPE_CODE 3
#define BE_TYPE_DATA 4
#define BE_TYPE_ELF32 5


#define be_code_vaddr be_extra0
#define be_code_ventr be_extra1

