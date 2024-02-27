int LoginAdministrator()
{
	FILE * ad; 
	int a=0;   //保存判断条件 
	int account;
	int password;    //接受用户输入 
	Administrator admini;
	printf("请输入管理员账号\n")
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen();//打开储存管理员信息的文件
	if(ad==NULL)
     {
      printf("打开文件失败.\n");
      exit(0);
     }
    fread(&admini,sizeof(Administrator),1,ad); //从文件中读取结构体; 
	for(;admini.next!=NULL;)
	{
		while(admini.account==account&&a==0)
		{
			fclose(ad);     //找到对应管理员，关闭文件 
			printf("请输入密码\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0;     //用于储存判断信息 
			if(password==admini.password)
			{
				printf("欢迎尊贵的管理员%s登录",admin.name);
				while(1)
				{
					
					printf("输入1查询商品记录\n输入3退出") //之后再补充 
					switch (i)
                  {
                    case 1:
                    printf("1层开!\n");
                    break;
                    case 2:
                    printf("2层开!\n");
                    break;
                    case 3:
                    printf("3层开!\n");
                    return 2;             //输入3，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
                    break;
                    default:
                    printf("该层不存在, 请重新输入\n");
				  }
				}
			}
			else
			{
				printf("输入2退出，输入任意数字重新输入\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //用一个int接受返回的值，判断是否登录成功 
				}
			} 
			
			
		}
		fread(&admini,sizeof(Administrator),1,ad);    //读取下一个 
	}
	while(admini.account==account&&a==0)
		{
			fclose(ad);     //找到对应管理员，关闭文件 
			printf("请输入密码\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0;     //用于储存判断信息 
			if(password==admini.password)
			{
				printf("欢迎尊贵的管理员%s登录",admin.name);
				while(ture)
				{
					printf("输入1查询商品记录\n输入3退出") //之后再补充 
					switch (i)
                  {
                    case 1:
                    printf("1层开!\n");
                    break;
                    case 2:
                    printf("2层开!\n");
                    break;
                    case 3:
                    printf("3层开!\n");
                    return 2;             //输入3，结束登录函数，返回大厅，通过返回值判断是否登录成功。 
                    break;
                    default:
                    printf("该层不存在, 请重新输入\n");
				  }
				}
			}
			else
			{
				printf("输入2退出，输入任意数字重新输入\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //用一个int接受返回的值，判断是否登录成功 
				}
			} 
	fclose(ad);    //找不到，关闭文件 
	printf("该管理员账号不存在！！！\n"); 
}
