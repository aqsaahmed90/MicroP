
int keypadUse = 0;

int pressedKey(int row, int col)
{
	if(row == 4 && col == 1){
		//EVAL_AUDIO_PauseResume(0);
		keypadUse = 1;
		return 10;
		
	}
	
	if (row == 4 && col == 3) {
	//	EVAL_AUDIO_PauseResume(1);
		keypadUse = 0;
		return 11;
		
	}
	
  if (keypadUse == 1) {
	//	EVAL_AUDIO_PauseResume(1);
		if(row == 1 && col == 1){
			
			return 1;
			
		}
		
		else if(row == 1 && col == 2){
			
			return 2;
			
		}
		else if(row == 1 && col == 3){
			
			return 3;
			
		}
		else if(row == 2 && col == 1){
						
			return 4;
			
		}
		else if(row == 2 && col == 2){
			
			return 5;
			
		}
		else if(row == 2 && col == 3){
			
			return 6;
			
		}
		else if(row == 3 && col == 1){
			
			return 7;
			
		}
		else if(row == 3 && col == 2){
			
			return 8;
			
		}
		else if(row == 3 && col == 3){
			
			return 9;
			
		}
		else if(row == 4 && col == 2){
			
			return 0;
			
		}
}

	return 11;
	
}
