include "autocompleter.h"

Autocompleter::Autocompleter()
{
	root = nullptr;
}

// Extra helper function

void updateTop(vector<Entry>& top, const Entry& entry){
	if (top.size() == 0){
    	top.push_back(entry);
    }
    else if (top.size() == 1){
    	if (entry.freq > top[0].freq)
    		top.insert(top.begin(), entry);
    	else
    		top.push_back(entry);
    }
    else if (top.size() == 2){
    	if (entry.freq > top[0].freq)
    		top.insert(top.begin(), entry);
    	else if (entry.freq > top[1].freq)
    		top.insert(top.begin() + 1, entry);
    	else
    		top.push_back(entry);
    }
    else{
    	if (entry.freq > top[0].freq){
    		top.insert(top.begin(), entry);
    		top.pop_back();
    	} else if (entry.freq > top[1].freq){
    		top.insert(top.begin() + 1, entry);
    		top.pop_back();
    	} else if (entry.freq > top[2].freq){
    		top.insert(top.begin() + 2, entry);
    		top.pop_back();
    	}
    }
}

void Autocompleter::insert(string x, int freq){
	Node* arrow = root;
	Entry newEntry;
    newEntry.s = x;
    newEntry.freq = freq;

    updateTop(root->top, newEntry);

	for (int i = 0; i < x.length(); i++){
		if (arrow->children[x[i]] == nullptr)
			arrow->children[x[i]]= new Node;

		arrow = arrow->children[x[i]];
		updateTop(arrow->top, newEntry);
	}

	if (arrow->marked == true){	// Word exists, get out
		return;
	}
	arrow->marked = true;
	count++;
}

int Autocompleter::size(){
	return count;
}

void Autocompleter::completions(string x, vector<string> &T){
	T.clear();		
	Node* arrow = root;

	for (int i = 0; i < x.length(); i++){
		if (arrow->children[x[i]] == nullptr)
			return;
		arrow = arrow->children[x[i]];
	}

	for (const Entry& entry : arrow->top){
		T.push_back(entry.s)
	}
}