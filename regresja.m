function regr = regresja( v, n, delta = 1 )

	lenv = length(v);
	if( lenv < n )
		regr = [NaN];
		return;
	endif

	regr = zeros(lenv-n+1,1);

	DELTA = 12/(delta*n*(n*n-1));
	sy = sum(v(1:n));
	sxy = sum(v(1:n).*[1:n])

	for l = 1:length(regr)
		regr(l) = DELTA*(sxy-(n+1)/2*sy);
		if( l != length(regr) )
			sxy=sxy-sy+n*v(n+l);
			sy=sy-v(l)+v(n+l);
		endif
	endfor

endfunction
