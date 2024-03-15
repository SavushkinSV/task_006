from subprocess import run, PIPE
import pytest

B_FILE_PATH = './bin/cafe'

def test_cafe_1():
    result = run([B_FILE_PATH], input='ORDER\npizza\n500\nbeer\n200\nBAR\nKITCHEN\nEXIT\n', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'beer\npizza\n'

def test_cafe_2():
    result = run([B_FILE_PATH], input='ORDER\npizza\n500\nbeer\n200\nORDER\nsoup\n300\ncola\n100\nBAR\nBAR\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'beer\ncola\n'

def test_cafe_3():
    result = run([B_FILE_PATH], input='ORDER\npizza\n500\nbeer\n200\nKITCHEN\nSTATS\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza\nKITCHEN 1 500\nBAR 0 0\n'

def test_cafe_4():
    result = run([B_FILE_PATH], input='STATS\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'KITCHEN 0 0\nBAR 0 0\n'

def test_cafe_5():
    result = run([B_FILE_PATH], input='CHECKOUT\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'UNKNOWN COMMAND\n'

def test_cafe_6():
    result = run([B_FILE_PATH], input='ORDER\npizza chips burger\n1500\ncola cola whiskey\n600\nKITCHEN\nBAR\nSTATS\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza chips burger\ncola cola whiskey\nKITCHEN 1 1500\nBAR 1 600\n'

def test_cafe_7():
    result = run([B_FILE_PATH], input='ORDER\npizza\n1500\ncola\n100\nORDER\npizza\n500\nwater\n0\nORDER\npizza\n500\ncola\n500\nKITCHEN\nKITCHEN\nKITCHEN\nBAR\nBAR\nBAR\nSTATS\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza\npizza\npizza\ncola\nwater\ncola\nKITCHEN 3 2500\nBAR 3 600\n'

def test_cafe_8():
    result = run([B_FILE_PATH], input='ORDER\npizza\n1500\ncola\n100\nORDER\npizza\n500\nwater\n0\nORDER\npizza\n500\ncola\n500\nKITCHEN\nKITCHEN\nKITCHEN\nBAR\nBAR\nBAR\nBAR\nSTATS\nEXIT', encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == 'pizza\npizza\npizza\ncola\nwater\ncola\nNO ORDERS\nKITCHEN 3 2500\nBAR 3 600\n'


if __name__ == "__main__":
    pytest.main()