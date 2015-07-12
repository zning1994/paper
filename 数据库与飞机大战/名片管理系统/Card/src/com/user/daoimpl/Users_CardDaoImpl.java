package com.user.daoimpl;

import java.util.ArrayList;
import java.util.List;

import com.manager.entity.Users_Card;
import com.user.dao.User_CardDaoInterface;


public class Users_CardDaoImpl extends com.manager.dao.BaseDao implements User_CardDaoInterface{

	public int insert(Users_Card uc) {
		// TODO Auto-generated method stub
		String sql = "insert into Users_Card(usersid,cardid) values(?,?)";
		List params=new ArrayList();
		params.add(uc.getUsersId());
		params.add(uc.getCardId());
		int i = super.executeUpdate(sql, params);
		return i;
	}

}
