entry = "types.txt"

lines = [line.rstrip('\n') for line in open(entry)]

output = "types_out.txt"



#f = open(output, "w")

new_token_list = []

for i in range(len(lines)):
	line_str = "#define "+lines[i]+' '+str(i)+'\n'
	new_token_list += line_str
#	f.write(line_str)



new_token_list += "#define TOKEN_LIST_AS_STRINGS()\\\n"

for i in range(len(lines)):
	line_str = '"'+lines[i]+'",\\\n'
	new_token_list += line_str
	#f.write(line_str)

#f.close()



cfile = "../src/headers/tokens.h"

lines = [line.rstrip('\n') for line in open(cfile)]

start = lines.index("//TOKENS_BEGIN")
end = lines.index("//TOKENS_END")

#print(*lines,sep='\n')

#print(start,end)

f = open(cfile,"w")

i = 0
while(i < len(lines) ):
	if(i <= start or i >= end):
		#print(lines[i])
		f.write(lines[i]+'\n')
		i += 1
	else:
		f.write("//Autogenerated by helper/token_creator.py\n")
		for q in range(len(new_token_list)):
			f.write(new_token_list[q])
		i = end
