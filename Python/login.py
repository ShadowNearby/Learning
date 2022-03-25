from time import sleep
from cv2 import imread
from selenium import webdriver
from selenium.webdriver.common.by import By
import re
import pytesseract
from PIL import Image, ImageEnhance
import os
chrome_options = webdriver.ChromeOptions()
chrome_options.add_argument('--ignore-certificate-errors')
chrome_options.add_argument('-ignore -ssl-errors')
driver = webdriver.Chrome(options=chrome_options)
driver.get('https://oc.sjtu.edu.cn/login/openid_connect')
while(re.match(r'^https://jaccount.sjtu.edu.cn/jaccount/', driver.current_url)):
    driver.implicitly_wait(30)
    driver.find_element(By.ID,'user').clear()
    driver.find_element(By.ID,'user').send_keys('yanjingsheng')#填入ID
    driver.find_element(By.ID,'pass').clear()
    driver.find_element(By.ID,'pass').send_keys('yjs135790')#填入密码
    driver.find_element(By.ID,'captcha').clear()
    screenImg = 'D:/screenImg.png'
    driver.get_screenshot_as_file(screenImg)
    location = driver.find_element(By.ID, 'captcha-img').location
    size = driver.find_element(By.ID, 'captcha-img').size
    left = location['x']
    top = location['y']
    right = location['x'] + size['width']
    bottom = location['y'] + size['height']
    img = Image.open(screenImg).crop((left + 200, top + 90, right + 230,bottom + 100))
    img = img.convert('RGBA')
    img = img.convert('L')
    img = ImageEnhance.Contrast(img)
    img = img.enhance(2.0)
    img.save(screenImg)
    img = Image.open(screenImg)
    code = pytesseract.image_to_string(img)
    os.remove('D:/screenImg.png')
    verification_code = ''
    for i in code.strip():
        pattern = re.compile(r'[a-zA-Z0-9]')
        search_result = pattern.search(i)
        if search_result != None:
            verification_code += i
    driver.find_element(By.ID,'captcha').send_keys(verification_code)
    webdriver.ActionChains(driver).move_to_element(driver.find_element(By.ID,'submit-button')).click(driver.find_element(By.ID,'submit-button')).perform()
    if(re.match(r'^https://oc.sjtu.edu.cn/', driver.current_url)):
        print('login success!')
        break