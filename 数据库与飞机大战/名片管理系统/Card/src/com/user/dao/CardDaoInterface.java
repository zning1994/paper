package com.user.dao;

import com.manager.entity.Card;

public interface CardDaoInterface {
	public int insert(Card c);
	public int findId();
	public int update(Card c);

}
