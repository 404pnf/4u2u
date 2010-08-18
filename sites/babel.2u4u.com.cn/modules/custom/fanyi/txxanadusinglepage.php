<?php
require "txgenerictools.php";

class TXXanaduSinglePageComm
{
	public $pageID;
	public $originalText;
	public $translationText;
	public $bookID;
	public $bookNameOriginal;
	public $bookNameTranslation;
	public $chapterID;
	public $chapterNameOriginal;
	public $chapterNameTranslation;
	public $comments;
	public $remark;
	
	public $error;

	function __construct()
	{
		$this->error = "";
//		$this->originalText = "";
//		$this->translationText = "";
	}

	public function setError($str)
	{
		if (TX::isNullOrEmptyString($str))
		{
			$this->error = "未知错误";
		}
		else
		{
			$this->error = $str;
		}

	}

	public function setOriginal($str)
	{
		if (TX::isNullOrEmptyString($str))
		{
			$this->originalText = "";
		}
		else
		{
			$this->originalText = $str;
		}

	}

	public function setTranslation($str)
	{
		if (TX::isNullOrEmptyString($str))
		{
			$this->translationText = "";
		}
		else
		{
			$this->translationText = $str;
		}

	}

	public function ifSuccess()
	{
		if (TX::isNullOrEmptyString($this->error))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
}

?>