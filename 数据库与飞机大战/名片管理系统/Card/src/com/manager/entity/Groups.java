package com.manager.entity;

import java.util.Date;


public class Groups {
	private int GroupId;
	private String GroupName;
	private int FatherGroupId;
	private String Notes;
	private int Sharing;
	private int UsersId;
	private Date CreateTime;
	public int getGroupId() {
		return GroupId;
	}
	public void setGroupId(int groupId) {
		GroupId = groupId;
	}
	public String getGroupName() {
		return GroupName;
	}
	public void setGroupName(String groupName) {
		GroupName = groupName;
	}
	public int getFatherGroupId() {
		return FatherGroupId;
	}
	public void setFatherGroupId(int fatherGroupId) {
		FatherGroupId = fatherGroupId;
	}
	public String getNotes() {
		return Notes;
	}
	public void setNotes(String notes) {
		Notes = notes;
	}
	public int getSharing() {
		return Sharing;
	}
	public void setSharing(int sharing) {
		Sharing = sharing;
	}
	public int getUsersId() {
		return UsersId;
	}
	public void setUsersId(int usersId) {
		UsersId = usersId;
	}
	public Date getCreateTime() {
		return CreateTime;
	}
	public void setCreateTime(Date createTime) {
		CreateTime = createTime;
	}
	

}
