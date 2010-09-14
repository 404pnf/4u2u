<?php
class TX
{
	public function getResultText($text, $type="info")
	{
		$result;

		if ($type == "error")
		{
			$result = "<font style='font-size: 11px' color='red' face='Arial'>".$text."</font>";
		}
		else if ($type == "success")
		{
			$result = "<font style='font-size: 11px' color='green' face='Arial'>".$text."</font>";
		}
		else if ($type == "info")
		{
			$result = "<font style='font-size: 11px' color='black' face='Arial'>".$text."</font>";
		}
		else
		{
			$result = "<font style='font-size: 11px' color='gray' face='Arial'>".$text."</font>";
		}

		return $result;
	}

	public function isNullOrEmptyString($str)
	{
		if (empty($str))
		{
			return true;
		}
		if (!is_string($str))
		{
			return true;
		}
		if ($str == "")
		{
			return true;
		}
		
		return false;
	}
}

?>