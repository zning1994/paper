package com.user.action;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.OutputStream;

import javax.servlet.http.HttpSession;

import org.apache.struts2.ServletActionContext;

import com.manager.dao.impl.CompanyDaoImpl;
import com.manager.dao.impl.DepartmentDaoImpl;
import com.manager.dao.impl.PositionDaoImpl;
import com.manager.entity.Card;
import com.manager.entity.Card_Users;
import com.manager.entity.Users;
import com.manager.entity.Users_Card;
import com.user.daoimpl.CardDaoImpl;
import com.user.daoimpl.Card_UsersDaoImpl;
import com.user.daoimpl.Users_CardDaoImpl;

public class CardModifyAction extends com.opensymphony.xwork2.ActionSupport{
	private File[] myFile;
	private String[] myFileFileName;
	private String usernameS;
	private String company;
	private String department;
	private String position;
	private String homeaddress;
	private int postcode;
	private String tel;
	private String mailbox;
	private String remark;
	private int carspower;
	private int cardid;
	private int state;
	public int getState() {
		return state;
	}
	public void setState(int state) {
		this.state = state;
	}
	public int getCardid() {
		return cardid;
	}
	public void setCardid(int cardid) {
		this.cardid = cardid;
	}
	public File[] getMyFile() {
		return myFile;
	}
	public void setMyFile(File[] myFile) {
		this.myFile = myFile;
	}
	public String[] getMyFileFileName() {
		return myFileFileName;
	}
	public void setMyFileFileName(String[] myFileFileName) {
		this.myFileFileName = myFileFileName;
	}
	public String getUsernameS() {
		return usernameS;
	}
	public void setUsernameS(String usernameS) {
		this.usernameS = usernameS;
	}
	public String getCompany() {
		return company;
	}
	public void setCompany(String company) {
		this.company = company;
	}
	public String getDepartment() {
		return department;
	}
	public void setDepartment(String department) {
		this.department = department;
	}
	public String getPosition() {
		return position;
	}
	public void setPosition(String position) {
		this.position = position;
	}
	public String getHomeaddress() {
		return homeaddress;
	}
	public void setHomeaddress(String homeaddress) {
		this.homeaddress = homeaddress;
	}
	public int getPostcode() {
		return postcode;
	}
	public void setPostcode(int postcode) {
		this.postcode = postcode;
	}
	public String getTel() {
		return tel;
	}
	public void setTel(String tel) {
		this.tel = tel;
	}
	public String getMailbox() {
		return mailbox;
	}
	public void setMailbox(String mailbox) {
		this.mailbox = mailbox;
	}
	public String getRemark() {
		return remark;
	}
	public void setRemark(String remark) {
		this.remark = remark;
	}
	public int getCarspower() {
		return carspower;
	}
	public void setCarspower(int carspower) {
		this.carspower = carspower;
	}
	
	public String execute() throws Exception{
		Card card = new Card();
		card.setCardId(getCardid());
		card.setState(getCarspower());
		card.setNotes(getRemark());
		card.setFront(myFileFileName[0]);
		System.out.println("cardmodifyaction"+myFileFileName[0]);
		card.setBehind(myFileFileName[1]);
		card.setState(state);
		CardDaoImpl cdi = new CardDaoImpl();
		cdi.update(card);
		
		
		Card_Users cu = new Card_Users();
		cu.setCardId(getCardid());
		//System.out.println("cardmodifyaction getCardid()"+getCardid());
		cu.setAddress(getHomeaddress());
		System.out.println(getHomeaddress()+"getHomeaddress()");
		cu.setCardUsersName(getUsernameS());
		CompanyDaoImpl cdi1 = new CompanyDaoImpl();
		cu.setCompanyId(cdi1.findByName(getCompany()));
		cu.setTel(getTel());
		cu.setPostCode(this.getPostcode());
		cu.setEmail(getMailbox());
		DepartmentDaoImpl dp = new DepartmentDaoImpl();
		cu.setDepartmentId(dp.findByName(getCompany(), getDepartment()));
		PositionDaoImpl psd = new PositionDaoImpl();
		cu.setPositionId(psd.findByName(getCompany(), getDepartment(), getPosition()));
		CardDaoImpl cdl = new CardDaoImpl();
		//System.out.println("uploadaction"+cdl.findId());
		cu.setCardId(cdl.findId());
		//System.out.println("uploadaction2"+cu.getCardId());
		Card_UsersDaoImpl cui = new Card_UsersDaoImpl();
		cui.update(cu);
		//System.out.println("cui.insert(cu)"+cui.insert(cu));//cui.insert(cu);
		
		
		
//		Users_Card uc = new Users_Card();
//		HttpSession session=ServletActionContext.getRequest().getSession();
//		//uc.setCardId(cardId)
//		//ActionContext c = ActionContext.getContext();
//		//HttpSession session=(HttpSession) c.getSession();
//		Users users=(Users) session.getAttribute("users");
//		//Users users = (Users) c.getSession().get("users");
//		CardDaoImpl uccdl = new CardDaoImpl();
//		uc.setCardId(uccdl.findId());
//		//uc.setCardId(cardId)    //先将card插入数据库，再从数据库查cardId
//		System.out.println("uploadaction2   users.getUsersId()"+users.getUsersId());
//		uc.setUsersId(users.getUsersId());
//		com.user.dao.impl.Users_CardDaoImpl ucdi = new com.user.dao.impl.Users_CardDaoImpl();
//		ucdi.update(uc);
//		
		
		OutputStream output=null;
		InputStream input=null;
		System.out.println("cardmodifyaction  name"+usernameS);
		try{
		for(int i=0;i<myFileFileName.length;i++){
			output=new FileOutputStream("e:/temp/"+myFileFileName[i]);
			//output=new FileOutputStream("temp/"+myFileFileName[i]);
			byte[] bs=new byte[1024];
	
				input = new FileInputStream(myFile[i]);
				int length=0;
				while((length=input.read(bs))>0){
					
					output.write(bs,0,length);
				}


			
		}
		}catch(Exception e){}
		finally{
			
			input.close();
			output.close();
		}
		
		return SUCCESS;
	}

}
