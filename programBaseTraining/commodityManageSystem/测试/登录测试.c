int LoginAdministrator()
{
	FILE * ad; 
	int a=0;   //�����ж����� 
	int account;
	int password;    //�����û����� 
	Administrator admini;
	printf("���������Ա�˺�\n")
	scanf("%d",&account);
	setbuf(stdin, NULL);
	ad=fopen();//�򿪴������Ա��Ϣ���ļ�
	if(ad==NULL)
     {
      printf("���ļ�ʧ��.\n");
      exit(0);
     }
    fread(&admini,sizeof(Administrator),1,ad); //���ļ��ж�ȡ�ṹ��; 
	for(;admini.next!=NULL;)
	{
		while(admini.account==account&&a==0)
		{
			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
			printf("����������\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0;     //���ڴ����ж���Ϣ 
			if(password==admini.password)
			{
				printf("��ӭ���Ĺ���Ա%s��¼",admin.name);
				while(1)
				{
					
					printf("����1��ѯ��Ʒ��¼\n����3�˳�") //֮���ٲ��� 
					switch (i)
                  {
                    case 1:
                    printf("1�㿪!\n");
                    break;
                    case 2:
                    printf("2�㿪!\n");
                    break;
                    case 3:
                    printf("3�㿪!\n");
                    return 2;             //����3��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
                    break;
                    default:
                    printf("�ò㲻����, ����������\n");
				  }
				}
			}
			else
			{
				printf("����2�˳�����������������������\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //��һ��int���ܷ��ص�ֵ���ж��Ƿ��¼�ɹ� 
				}
			} 
			
			
		}
		fread(&admini,sizeof(Administrator),1,ad);    //��ȡ��һ�� 
	}
	while(admini.account==account&&a==0)
		{
			fclose(ad);     //�ҵ���Ӧ����Ա���ر��ļ� 
			printf("����������\n");
			scanf("%d",&password);
			setbuf(stdin, NULL);
			int i=0,k=0;     //���ڴ����ж���Ϣ 
			if(password==admini.password)
			{
				printf("��ӭ���Ĺ���Ա%s��¼",admin.name);
				while(ture)
				{
					printf("����1��ѯ��Ʒ��¼\n����3�˳�") //֮���ٲ��� 
					switch (i)
                  {
                    case 1:
                    printf("1�㿪!\n");
                    break;
                    case 2:
                    printf("2�㿪!\n");
                    break;
                    case 3:
                    printf("3�㿪!\n");
                    return 2;             //����3��������¼���������ش�����ͨ������ֵ�ж��Ƿ��¼�ɹ��� 
                    break;
                    default:
                    printf("�ò㲻����, ����������\n");
				  }
				}
			}
			else
			{
				printf("����2�˳�����������������������\n");
				scanf("%d",&k);
				setbuf(stdin, NULL);
				if(k==2)
				{
					return 1;    //��һ��int���ܷ��ص�ֵ���ж��Ƿ��¼�ɹ� 
				}
			} 
	fclose(ad);    //�Ҳ������ر��ļ� 
	printf("�ù���Ա�˺Ų����ڣ�����\n"); 
}
