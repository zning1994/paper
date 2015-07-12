package com.user.daoimpl;

import java.util.ArrayList;
import java.util.List;

import com.manager.dao.BaseDao;
import com.manager.entity.Card_Users;
import com.user.dao.Card_UsersDaoInterface;

public class Card_UsersDaoImpl extends BaseDao implements Card_UsersDaoInterface{

	public int insert(Card_Users cu) {
		// TODO Auto-generated method stub
		String sql = "insert into Card_users(cardid,address,cardusersname,companyid,tel,postcode,email,departmentid,positionid) values(?,?,?,?,?,?,?,?,?)";
		String address = cu.getAddress();
		String cardusersname = cu.getCardUsersName();
		int cardid = cu.getCardId();
		int companyid = cu.getCompanyId();
		String tel = cu.getTel();
		int postcode = cu.getPostCode();
		String emal = cu.getEmail();
		List params=new ArrayList();
		params.add(cardid);
		params.add(address);
		params.add(cardusersname);
		params.add(companyid);
		params.add(tel);
		params.add(postcode);
		params.add(emal);
		params.add(cu.getDepartmentId());
		params.add(cu.getPositionId());
		int i = super.executeUpdate(sql, params);
		return i;
	}

	public int update(Card_Users cu) {
		// TODO Auto-generated method stub
		String sql = "update card_users ";
		List params = new ArrayList();
		String set = "";
		if(cu.getAddress()!=null&&!"".equals(cu.getAddress())){
			set+=",address=?";
			params.add(cu.getAddress());
		}
		if(cu.getCardUsersName()!=null&&!"".equals(cu.getCardUsersName())){
			set+=",cardusersname=?";
			params.add(cu.getCardUsersName());
		}
		if(cu.getPostCode()!=0&&!"".equals(cu.getPostCode())){
			set+=",postcode=?";
			params.add(cu.getPostCode());
		}
		if(cu.getEmail()!=null&&!"".equals(cu.getEmail())){
			set+=",email=?";
			params.add(cu.getEmail());
		}
		if(cu.getTel()!=null&&!"".equals(cu.getTel())){
			set+=",tel=?";
			params.add(cu.getTel());
		}
		if(cu.getCompanyId()!=0){
			set+=",companyid=?";
			params.add(cu.getCompanyId());
		}
		if(cu.getDepartmentId()!=0){
			set+=",departmentid=?";
			params.add(cu.getDepartmentId());
		}
		if(cu.getPositionId()!=0){
			set+=",positionid=?";
			params.add(cu.getPositionId());
		}
		sql+=" set " +set.substring(1);
		sql+=" where cardid=?";
		params.add(cu.getCardId());
		System.out.println("card_userdaoimpl"+cu.getCardId());
		int i=super.executeUpdate(sql, params);
		return i;
	}

}
