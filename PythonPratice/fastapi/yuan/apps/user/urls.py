
from fastapi import APIRouter

user = APIRouter()

@user.get("/name")
def user_name():
    return {"user": "name"}

@user.get("/passwd")
def user_passwd():
    return {"user": "passwd"}
