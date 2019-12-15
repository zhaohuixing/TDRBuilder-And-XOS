<?xml version = "1.0" ?><!-- /*Begin Test*/ --><xpl version = "1.0">
<module name = "csc" date = "Tue Mar 22 16:20:17 2005
">
<entry>
<input>
<variable type = "float" name = "iv1" default_value = "0.000000e+000"/>
</input></entry><initialize>
<next id = "0"/>
<global/>
<local>
<variable type = "float" name = "lv1" default_value = "0.000000e+000"/>


</local></initialize><processor name = "Processor" id = "0" type = "3">
<previous id = "-3"/>
<next id = "-4"/>
<method>
<![CDATA[
long Processor(void)
{
	lv1 = 2.689;
	iv1 = csc(lv1);
	m_nRegister = -4;
	return m_nRegister;
}]]>
</method>

</processor></module></xpl><!-- /*End Test*/ -->